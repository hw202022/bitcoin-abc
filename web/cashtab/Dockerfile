# Multi-stage
# 1) Node image for building frontend assets
# 2) nginx stage to serve frontend assets

# Stage 1
FROM node:15-buster-slim AS builder
# Set working directory
WORKDIR /app
# Copy all files from current directory to working dir in image
COPY . .
# Install git, required for installing some npm modules
RUN apt-get update && \
  apt-get upgrade -y && \
  apt-get install -y git && \
  apt-get install -y python
# install node modules and build assets
RUN npm install --legacy-peer-deps && npm run build

# Stage 2
FROM nginx
COPY nginx.conf /etc/nginx/conf.d/default.conf
# Set working directory to nginx asset directory
# Copy static assets from builder stage
COPY --from=builder /app/build /usr/share/nginx/html/
EXPOSE 80
# Containers run nginx with global directives and daemon off
ENTRYPOINT ["nginx", "-g", "daemon off;"]